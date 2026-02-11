pub_txt_ready()
	{
		if(pub_txt.success())
		{
			have_txt = true;

			if(need_update_txt)
			{
				need_update_txt = false;
				doPublishTxt();
			}

			tryDone();
		}
		else
		{
			JDnsSharedRequest::Error e = pub_txt.error();
			cleanup();
			emit error(e);
		}
	}
