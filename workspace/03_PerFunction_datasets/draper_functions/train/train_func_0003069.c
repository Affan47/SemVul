chooseProfile()
{
	if(pcon) {
		delete pcon;
		pcon = 0;
	}

	QString str = "";


	PsiIconset::instance()->loadSystem();

	while(1) {
		ProfileOpenDlg *w = new ProfileOpenDlg(lastProfile, TranslationManager::instance()->availableTranslations(), TranslationManager::instance()->currentLanguage());
		w->ck_auto->setChecked(autoOpen);
		int r = w->exec();

		if(r == 10) {
			TranslationManager::instance()->loadTranslation(w->newLang);
			lastLang = TranslationManager::instance()->currentLanguage();
			delete w;
			continue;
		}
		else {
			bool again = false;
			autoOpen = w->ck_auto->isChecked();
			if(r == QDialog::Accepted) {
				str = w->cb_profile->currentText();
				again = !ActiveProfiles::instance()->setThisProfile(str);
				if (again) {
					QMessageBox mb(QMessageBox::Question,
						CAP(tr("Profile already in use")),
						QString(tr("The \"%1\" profile is already in use.\nWould you like to activate that session now?")).arg(str),
						QMessageBox::Cancel);
					QPushButton *activate = mb.addButton(tr("Activate"), QMessageBox::AcceptRole);
					mb.exec();
					if (mb.clickedButton() == activate) {
						ActiveProfiles::instance()->raiseOther(str, true);
						quit();
						return;
					}
				}
			}
			delete w;
			if (again) {
				str = "";
				continue;
			}
			break;
		}
	}

	if(str.isEmpty()) {
		quit();
		return;
	}


	lastProfile = str;

	activeProfile = str;
	sessionStart();
}
