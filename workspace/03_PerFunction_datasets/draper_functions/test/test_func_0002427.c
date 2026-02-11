edb_finished()
{
	const EDBResult *r = d->h->result();
	if(d->h->lastRequestType() == EDBHandle::Read && r) {

		if(r->count() > 0) {
			Q3PtrListIterator<EDBItem> it(*r);
			if(d->reqtype == 0 || d->reqtype == 1) {


				it.toFirst();
				d->id_end = it.current()->id();
				d->id_next = it.current()->nextId();

				it.toLast();
				d->id_begin = it.current()->id();
				d->id_prev = it.current()->prevId();
				displayResult(r, EDB::Backward);

			}
			else if(d->reqtype == 2) {


				it.toLast();
				d->id_end = it.current()->id();
				d->id_next = it.current()->nextId();

				it.toFirst();
				d->id_begin = it.current()->id();
				d->id_prev = it.current()->prevId();
				displayResult(r, EDB::Forward);
			}
			else if(d->reqtype == 3) {

				EDBItem *ei = it.current();
				d->reqtype = 1;
				d->h->get(d->jid, ei->id(), EDB::Backward, 50);

				return;
			}
		}
		else {
			if(d->reqtype == 3) {
				QMessageBox::information(this, tr("Find"), tr("Search string '%1' not found.").arg(d->findStr));
				return;
			}
		}
	}
	else if (d->h->lastRequestType() == EDBHandle::Erase) {
		if (d->h->writeSuccess()) {
			d->lv->clear();
			d->id_prev = "";
			d->id_begin = "";
			d->id_end = "";
			d->id_next = "";
		}
		else {
			QMessageBox::critical(this, tr("Error"), tr("Unable to delete history file."));
		}
	}
	else {

	}

	if(d->lv->firstChild())
		d->lv->setSelected(d->lv->firstChild(), true);


	d->pb_refresh->setEnabled(true);
	setButtons();
}
