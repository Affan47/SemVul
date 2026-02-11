wmConfirmKill() {
#ifndef LITE
    if (fKillMsgBox == 0) {
        YMsgBox *msgbox = new YMsgBox(YMsgBox::mbOK|YMsgBox::mbCancel);
        ustring title = ustring(_("Kill Client: ")).append(getTitle());
        fKillMsgBox = msgbox;

        msgbox->setTitle(title);
        msgbox->setText(_("WARNING! All unsaved changes will be lost when\n"
                          "this client is killed. Do you wish to proceed?"));
        msgbox->autoSize();
        msgbox->setMsgBoxListener(this);
        msgbox->showFocused();
    }
#endif
}
