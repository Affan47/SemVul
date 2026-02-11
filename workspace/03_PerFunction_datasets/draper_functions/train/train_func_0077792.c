captureScreens()
    {
        QDesktopWidget *desktop = QApplication::desktop();
        QList< QPair<QPixmap, QRect> > result;

        for(int screenIndex = 0; screenIndex < desktop->screenCount(); ++screenIndex)
        {
            const QRect &screenGeometry = desktop->screenGeometry(screenIndex);

            result.append(qMakePair(QPixmap::grabWindow(desktop->winId(), screenGeometry.x(), screenGeometry.y(), screenGeometry.width(), screenGeometry.height()), screenGeometry));
        }

        return result;
    }
