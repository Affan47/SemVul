getReadoutDirection(VimosPort *port)
{
  int vertical = 1;

  if (port->prScan->nX > 0
                           && port->window->startY == port->prScan->startY) {
    vertical = 0;
  }
  else if (port->ovScan->nX > 0
                           && port->window->startY == port->ovScan->startY) {
    vertical = 0;
  }

  return(vertical);
}
