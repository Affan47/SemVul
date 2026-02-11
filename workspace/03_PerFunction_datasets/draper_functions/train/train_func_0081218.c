restoreOptions()
{
	if ( !w )
		return;

	OptChatUI *d = (OptChatUI *)w;

	bg_defAct->buttons()[PsiOptions::instance()->getOption("options.messages.default-outgoing-message-type").toString() == "message" ? 0 : 1]->setChecked(true);
	d->ck_alertOpenChats->setChecked( PsiOptions::instance()->getOption("options.ui.chat.alert-for-already-open-chats").toBool() );
	d->ck_raiseChatWindow->setChecked( PsiOptions::instance()->getOption("options.ui.chat.raise-chat-windows-on-new-messages").toBool() );
	d->ck_smallChats->setChecked( PsiOptions::instance()->getOption("options.ui.chat.use-small-chats").toBool() );
	d->ck_tabChats->setChecked( PsiOptions::instance()->getOption("options.ui.tabs.use-tabs").toBool() );
	QString tabGrouping = PsiOptions::instance()->getOption("options.ui.tabs.grouping").toString();
	bool custom = false;
	if (tabGrouping == "C") {
		d->cb_tabGrouping->setCurrentIndex(0);
	} else if (tabGrouping == "M") {
		d->cb_tabGrouping->setCurrentIndex(1);
	} else if (tabGrouping == "C:M") {
		d->cb_tabGrouping->setCurrentIndex(2);
	} else if (tabGrouping == "CM") {
		d->cb_tabGrouping->setCurrentIndex(3);
	} else {
		if (d->cb_tabGrouping->count() == 5) {
			d->cb_tabGrouping->setCurrentIndex(4);
		} else {
			d->cb_tabGrouping->setCurrentIndex(-1);
		}
		custom = true;
	}
	if (!custom && d->cb_tabGrouping->count() == 5) {
		d->cb_tabGrouping->removeItem(4);
	}
	d->ck_autoResize->setChecked( PsiOptions::instance()->getOption("options.ui.chat.use-expanding-line-edit").toBool() );
	QString delafter = PsiOptions::instance()->getOption("options.ui.chat.delete-contents-after").toString();
	if (delafter == "instant") {
		d->rb_delChatsClose->setChecked(true);
	} else if (delafter == "hour") {
		d->rb_delChatsHour->setChecked(true);
	} else if (delafter == "day") {
		d->rb_delChatsDay->setChecked(true);
	} else if (delafter == "never") {
		d->rb_delChatsNever->setChecked(true);
	}
	d->ck_chatSoftReturn->setChecked(ShortcutManager::instance()->shortcuts("chat.send").contains(QKeySequence(Qt::Key_Return)));
}
