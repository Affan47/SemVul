popupMenu(const QPoint& point)
{
    QMenu popupMenu(_drawingWidget);
    popupMenu.addMenu(fileMenu);
    popupMenu.addMenu(editMenu);
    popupMenu.addMenu(movieControlMenu);
    popupMenu.addMenu(viewMenu);
    popupMenu.exec(point);
}
