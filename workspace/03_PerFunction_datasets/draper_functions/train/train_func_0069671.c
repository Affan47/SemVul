read(bool readProperties, Properties::ReadStyle propertiesStyle)
{


  scan();

  if (!d->scanned) {
    setValid(false);
    return;
  }


  if(d->hasXiphComment)
    d->comment = new Ogg::XiphComment(xiphCommentData());
  else
    d->comment = new Ogg::XiphComment;


  if(readProperties)
    d->properties = new Properties(streamInfoData(), streamLength(), propertiesStyle);
}
