ValueChanged (LinesDlg *pBox, unsigned row, unsigned column)
{
	double coord = column != COLUMN_SINGLE? gcr_grid_get_double (pBox->m_Grid, row, column): 0.;
	Line *line = pBox->m_Lines[pBox->m_LineSelected];
	switch (column) {
	case COLUMN_X1:
		line->X1 () = coord;
		break;
	case COLUMN_Y1:
		line->Y1 () = coord;
		break;
	case COLUMN_Z1:
		line->Z1 () = coord;
		break;
	case COLUMN_X2:
		line->X2 () = coord;
		break;
	case COLUMN_Y2:
		line->Y2 () = coord;
		break;
	case COLUMN_Z2:
		line->Z2 () = coord;
		break;
	case COLUMN_SINGLE:
		line->Type () = gcr_grid_get_boolean (pBox->m_Grid, row, column)? unique: normal;
	}
	pBox->m_pDoc->Update ();
	pBox->m_pDoc->SetDirty (true);
}
