Step(pkgTagSection &Tag)
{
   while (Tag.Scan(d->Start,d->End - d->Start) == false)
   {
      if (Fill() == false)
	 return false;

      if(Tag.Scan(d->Start,d->End - d->Start))
	 break;

      if (Resize() == false)
	 return _error->Error(_("Unable to parse package file %s (1)"),
                              d->Fd.Name().c_str());
   }
   d->Start += Tag.size();
   d->iOffset += Tag.size();

   Tag.Trim();
   return true;
}
