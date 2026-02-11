addRelativeLinear(QPointF end, int duration)
{
  AnimationCommand* cmd = new AnimationCommand();
  cmd->cmd = AnimationCommand::LINEAR_DURATION;
  cmd->duration = duration;
  cmd->start=previousEnd();
  cmd->end=end;
  mAnimList.append(cmd);
  return cmd;
}
