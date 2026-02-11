eventFilter(QObject *watched, QEvent *event)
{
  if (watched != area)
    return false;
  if (event->type() == QEvent::Resize)
    {
      QRect ar = area->rect().adjusted(+20,+20,-20,-20);
      foreach(Client *client, clients)
        if (client->subWindow &&
            ! ar.intersects(client->subWindow->frameGeometry()) )
          {

            QRect gr = client->subWindow->geometry();
            gr.moveRight(qMax(gr.right(), ar.left()));
            gr.moveLeft(qMin(gr.left(), ar.right()));
            gr.moveBottom(qMax(gr.bottom(), ar.top()));
            gr.moveTop(qMin(gr.top(), ar.bottom()));
            client->subWindow->setGeometry(gr);
          }
    }
  if (event->type() == QEvent::WindowActivate)
    guiUpdateLater();
  return false;
}
