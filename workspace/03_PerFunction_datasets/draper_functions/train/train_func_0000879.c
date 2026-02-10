delAttachment(std::string filename)
{
	restartAutosaveTimer();
	std::vector<AttachmentButton *>::iterator b, e, p;

	b=attachmentList.begin();
	e=attachmentList.end();

	while (b != e)
	{
		p=b;

		AttachmentButton *a= *b++;

		if (a && a->getFilename() == filename)
		{
			a->erase();
			bool needFocus=false;

			if (b != e && *b)
				(*b)->requestFocus();
			else
				needFocus=true;
			delete a;
			unlink(filename.c_str());
			*p=NULL;
			attachmentList.erase(p);
			resized();
			if (needFocus)
			{
				if (attachmentList.size() > 0 &&
				    attachmentList[attachmentList.size()-1])
					attachmentList[attachmentList.size()-1]
						->requestFocus();
				else
					newAttachment.requestFocus();
			}
			break;
		}
	}
}
