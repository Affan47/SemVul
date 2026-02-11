refreshDmodLogos()
{
  mAllLogos = wxBitmap(LOGO_WIDTH, (mDModListBox->GetCount()+1) * LOGO_HEIGHT);
  wxMemoryDC lAllDC(mAllLogos);
  lAllDC.DrawBitmap(mDefaultLogoBitmap, 0,0, false);

  for (unsigned int i = 0; i < mDModListBox->GetCount(); i++)
    {
      Integer *I = (Integer*)mDModListBox->GetClientObject(i);
      int cur_dmod_index = I->i;
      DMod cur_dmod = mAvailableDModsList.at(cur_dmod_index);

      wxBitmap lLogoBitmap;

      wxString lDmodPreview(cur_dmod.GetFullPath() + _T("/preview.bmp"));
      IOUtils::ciconvert(lDmodPreview);
      wxString lDmodTitle(cur_dmod.GetFullPath() + _T("/graphics/title-01.bmp"));
      IOUtils::ciconvert(lDmodTitle);
      if (::wxFileExists(lDmodPreview) == true)
	{
	  lLogoBitmap = wxBitmap(lDmodPreview, wxBITMAP_TYPE_BMP);
	}
      else if (::wxFileExists(lDmodTitle) == true)
	{
	  wxImage lImage(lDmodTitle);
	  lImage.Rescale(LOGO_WIDTH, LOGO_HEIGHT);
	  lLogoBitmap = wxBitmap(lImage);
	}
      else
	{
	  lLogoBitmap = CreateTextLogo(cur_dmod.GetBaseName());
	}
      lLogoBitmap.SetWidth(LOGO_WIDTH);
      lLogoBitmap.SetHeight(LOGO_HEIGHT);

      lAllDC.DrawBitmap(lLogoBitmap, 0,(i+1)*LOGO_HEIGHT, false);


    }
}
