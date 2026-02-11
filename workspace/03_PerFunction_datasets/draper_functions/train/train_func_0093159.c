beginProcessData(imap &imapAccount,
					   vector<const char *> &words,
					   unsigned long estimatedSize)
{
	doFetchingEnvelope=false;

	if (words.size() >= 2 && strcasecmp(words[0], "FETCH") == 0 &&
	    (attributes & (mail::account::ENVELOPE
			   |mail::account::MIMESTRUCTURE)))
	{
		size_t oldFetchingMessageNum=fetchingMessageNum;


		string n=words[1];
		istringstream i(n);

		fetchingMessageNum=0;

		i >> fetchingMessageNum;

		if (fetchingMessageNum > 0 &&
		    fetchingMessageNum <=
		    (imapAccount.currentFolder &&
		     !imapAccount.currentFolder->closeInProgress ?
		     imapAccount.currentFolder->exists:0))
		{
			if (attributes & mail::account::MIMESTRUCTURE)
			{
				if (doFetchingStructure &&
				    oldFetchingMessageNum
				    != fetchingMessageNum)
				{
					checkMimeVersion();
					msgcallback
						.messageStructureCallback(oldFetchingMessageNum-1,
									  fetchingStructure);
					fetchingStructure= mail::mimestruct();
					fetchingStructure.type="TEXT";
					fetchingStructure.subtype="PLAIN";
				}

				unsigned long mimeSize=0;
				string mimeid="";
				string mimeparent="";

				vector<const char *>::iterator
					b=words.begin()+2, e=words.end();

				while (b != e)
				{
					const char *c= *b++;

					if (strncasecmp(c, "SIZE=", 5) == 0)
					{
						string n=c+5;

						istringstream i(n);

						i >> mimeSize;
					}

					if (strncasecmp(c, "MIME.ID=", 8) == 0)
						mimeid=c+8;

					if (strncasecmp(c, "MIME.PARENT=", 12)
					    == 0)
					{
						mimeparent=c+12;
					}
				}

#if 0
				cerr << "new MIME struct: id="
				     << mimeid << ", parent=" << mimeparent
				     << endl;
#endif

				seenMimeVersion=false;
				if (fetchingStructCount > 1000)
				{
					doFetchingStructure=NULL;

				}
				else if (mimeid == "")
				{
					doFetchingStructure=
						&fetchingStructure;
				}
				else
				{
					mail::mimestruct *p=
						findMimeId(&fetchingStructure,
							   mimeparent, 0);

					doFetchingStructure=NULL;
					if (p)
					{
						doFetchingStructure=
							p->addChild();
						doFetchingStructure->type
							="TEXT";
						doFetchingStructure->subtype
							="PLAIN";
					}
				}

				if (doFetchingStructure)
				{
					++fetchingStructCount;

#if 0
					cerr << "added " << mimeid
					     << ", parent's numChildren="
					     << (doFetchingStructure
						 ->getParent()
						 ? doFetchingStructure
						 ->getParent()->getNumChildren()
						 : 0) << endl;
#endif

					doFetchingStructure->mime_id=mimeid;
					doFetchingStructure->content_size=
						mimeSize;
				}
			}

			doFetchingEnvelope=true;
			fetchingEnvelope= mail::envelope();
			fetchingHeader="";
		}
	}
}
