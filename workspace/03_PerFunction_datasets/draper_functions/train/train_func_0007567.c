mousePressEvent(QMouseEvent* mouseEvent)
{
   if(mouseEvent->button() & Qt::LeftButton) {
      selection(0, 0, 0, 0);
      getMarkPosition(mouseEvent, MarkX1, MarkY1);
      MarkX2  = MarkX1;
      MarkY2  = MarkY1;
      Marking = true;
      update();
   }
}
