addShow()
{
  AnimationCommand* cmd = new AnimationCommand();
  cmd->cmd = AnimationCommand::SHOW;
  cmd->duration = 0;
  cmd->start=previousStart();
  cmd->end=previousEnd();
  mAnimList.append(cmd);
  return cmd;
}
