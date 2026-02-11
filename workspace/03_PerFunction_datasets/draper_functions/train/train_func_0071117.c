setPixmap(const QPixmap &pixmap, ImageAlignment alignment)
{
    d->imageLabel->setVisible(!pixmap.isNull());

    d->headerLayout->removeWidget(d->textLabel);
    d->headerLayout->removeWidget(d->commentLabel);
    d->headerLayout->removeWidget(d->imageLabel);

    if (alignment == ImageLeft) {

        d->headerLayout->addWidget(d->imageLabel, 0, 0, 2, 1);
        d->headerLayout->addWidget(d->textLabel, 0, 1);
        d->headerLayout->addWidget(d->commentLabel, 1, 1);
        d->headerLayout->setColumnStretch(0, 0);
        d->headerLayout->setColumnStretch(1, 1);
    } else {
        d->headerLayout->addWidget(d->textLabel, 0, 0);
        d->headerLayout->addWidget(d->commentLabel, 1, 0);
        d->headerLayout->addWidget(d->imageLabel, 0, 1, 2, 1);
        d->headerLayout->setColumnStretch(1, 0);
        d->headerLayout->setColumnStretch(0, 1);
    }

    d->imageLabel->setPixmap(pixmap);
}
