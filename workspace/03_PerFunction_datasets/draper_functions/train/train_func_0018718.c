pilFrmDuplicate(PilFrame *frame)
{

  PilFrame *copy = newPilFrame(frame->filename, frame->category);

  if (copy) {
    copy->type = frame->type;
    copy->format = frame->format;
    copy->attributes.level  = frame->attributes.level;
    copy->attributes.type  = frame->attributes.type;
    copy->flags.keep   = frame->flags.keep;
    copy->flags.ignore = frame->flags.ignore;
  }

  return copy;

}
