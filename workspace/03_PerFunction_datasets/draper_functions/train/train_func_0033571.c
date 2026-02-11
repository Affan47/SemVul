captureWindows(const QList<WindowHandle> &windows)
    {
        QDesktopWidget *desktop = QApplication::desktop();
        QList< QPair<QPixmap, QRect> > result;

        foreach(const WindowHandle &window, windows)
        {
            if(!window.isValid())
                continue;

            const QRect &windowGeometry = window.rect();

            result.append(qMakePair(QPixmap::grabWindow(desktop->winId(), windowGeometry.x(), windowGeometry.y(), windowGeometry.width(), windowGeometry.height()), windowGeometry));
        }

        return result;
    }
