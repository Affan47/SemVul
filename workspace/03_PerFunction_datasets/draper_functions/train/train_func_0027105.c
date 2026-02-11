duplicate(ball * pack)
{
  boringball * output = new boringball(pack);
  output->animate = animate;
  output->animatestate = animatestate;
  output->setcenter(center);
  output->setvelocity(velocity);
  output->setboundary(boundary);
  output->animate = animate;
  return output;
}
