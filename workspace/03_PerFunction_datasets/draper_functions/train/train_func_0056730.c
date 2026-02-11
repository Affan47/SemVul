pilRecListSet(PilSetOfFrames *set)
{

  PilFrame *frame = pilSofFirst(set);

  while (frame) {
    pilMsgInfo(pilRecGetName(), "%s (%s)", pilFrmGetName(frame),
	       pilFrmGetCategory(frame));
    frame = pilSofNext(set, frame);
  }

  return;

}
