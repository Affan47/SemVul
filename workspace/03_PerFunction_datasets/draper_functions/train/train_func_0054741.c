cmd_test (void)


{
  if (tokeneq (token[1], "movelist"))
    TestMoveList ();
  else if (tokeneq (token[1], "capture"))
    TestCaptureList ();
  else if (tokeneq (token[1], "movegenspeed"))
    TestMoveGenSpeed ();
  else if (tokeneq (token[1], "capturespeed"))
    TestCaptureGenSpeed ();
  else if (tokeneq (token[1], "eval"))
    TestEval ();
  else if (tokeneq (token[1], "evalspeed"))
    TestEvalSpeed ();
}
