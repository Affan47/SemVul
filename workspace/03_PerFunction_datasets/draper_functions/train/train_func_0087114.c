bindKeys()
{
    rotatecw = mpKeyShortcuts->addAction( QLatin1String( "rotate_cw" ));
    rotatecw->setText(i18n("Rotate Piece Clockwise"));
    rotatecw->setIcon(KIcon( QLatin1String( "object-rotate-right" )));
    rotatecw->setShortcuts( KShortcut( "z" ) );
    connect(rotatecw, SIGNAL(triggered(bool)), this, SLOT(rotateCW()));

    rotateccw = mpKeyShortcuts->addAction( QLatin1String( "rotate_ccw" ));
    rotateccw->setText(i18n("Rotate Piece Counter Clockwise"));
    rotateccw->setIcon(KIcon( QLatin1String( "object-rotate-left" )));
    rotateccw->setShortcuts( KShortcut( Qt::Key_Up  ) );
    connect(rotateccw, SIGNAL(triggered(bool)), this, SLOT(rotateCCW()));

    moveleft = mpKeyShortcuts->addAction( QLatin1String( "move_left" ));
    moveleft->setText(i18n("Move Piece Left"));
    moveleft->setIcon(KIcon( QLatin1String( "arrow-left" )));
    moveleft->setShortcuts( KShortcut( Qt::Key_Left ) );
    connect(moveleft, SIGNAL(triggered(bool)), this, SLOT(moveLeft()));

    moveright = mpKeyShortcuts->addAction( QLatin1String( "move_right" ));
    moveright->setText(i18n("Move Piece Right"));
    moveright->setIcon(KIcon( QLatin1String( "arrow-right" )));
    moveright->setShortcuts( KShortcut( Qt::Key_Right) );
    connect(moveright, SIGNAL(triggered(bool)), this, SLOT(moveRight()));

    movedown = mpKeyShortcuts->addAction( QLatin1String( "move_down" ));
    movedown->setText(i18n("Move Piece Down"));
    movedown->setIcon(KIcon( QLatin1String( "arrow-down" )));
    movedown->setShortcuts( KShortcut( Qt::Key_Down ) );
    connect(movedown, SIGNAL(triggered(bool)), this, SLOT(moveDown()));

    pushdown = mpKeyShortcuts->addAction( QLatin1String( "push_down" ));
    pushdown->setText(i18n("Drop the Piece"));
    pushdown->setIcon(KIcon( QLatin1String( "arrow-down" )));
    pushdown->setShortcuts( KShortcut( Qt::Key_Space ) );
    connect(pushdown, SIGNAL(triggered(bool)), this, SLOT(pushDown()));
}
