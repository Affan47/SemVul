okToWrite(QWidget* parent, const QString& file, QMessageBox::StandardButton& msgBoxButton)
{
	if(QFile::exists(file)){
		if(msgBoxButton==QMessageBox::YesToAll){
			return true;
		}
		else if(msgBoxButton==QMessageBox::NoToAll){
			return false;
		}
		else if(msgBoxButton==QMessageBox::No ||
		 msgBoxButton==QMessageBox::Yes ||
		 msgBoxButton==QMessageBox::NoButton){

			QMessageBox msgBox(parent);
			msgBox.setWindowTitle(tr("FET warning"));
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.setText(tr("File %1 exists - are you sure you want to overwrite existing file?").arg(file));
			msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::YesToAll|QMessageBox::NoToAll);
			msgBox.setDefaultButton(QMessageBox::Yes);

			msgBoxButton=((QMessageBox::StandardButton)(msgBox.exec()));


			if(msgBoxButton==QMessageBox::No || msgBoxButton==QMessageBox::NoToAll)
				return false;
			else
				return true;
		}
		else{
			assert(0);
			return false;
		}
	}
	else
		return true;
}
