showScreenShot()
{

    int id = d->ui->formsTreeView->currentIndex().data(IndexRole).toInt();
    if (id >= 0 && id < d->m_FormDescr.count()) {
        Form::FormIODescription *descr = d->m_FormDescr.at(id);

        Utils::ImageViewer dlg(this);
        dlg.setPixmaps(descr->screenShots());
        dlg.exec();
    }
}
