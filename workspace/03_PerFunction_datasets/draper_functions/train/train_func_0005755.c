queueRepaint() {
  global.debug("Board","queueRepaint");
  if (frozen_lvl)
    repaint_due=true;
  else
    repaint();
}
