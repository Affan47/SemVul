newTool(But *but, int val)  {
  EditToolWin  *etw;

  etw = but_packet(but);
  assert(MAGIC(etw));
  if ((EditTool)val != etw->tool)  {
    etw->tool = (EditTool)val;
    butText_set(etw->toolName, msg_toolNames[val]);
    butText_set(etw->toolDesc1, msg_toolDesc1[val]);
    butText_set(etw->toolDesc2, msg_toolDesc2[val]);
  }
  return(etw->newToolCallback(etw->packet));
}
