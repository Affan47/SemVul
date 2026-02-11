multKronBlock(const_diag_iter start, const_diag_iter end,
								  KronVector& x, Vector& work) const
{
	int si = (*start).getIndex();
	int ei = diagonal.getSize();
	if (end != diag_end())
		ei = (*end).getIndex();
	savePartOfX(si, ei, x, work);

	for (const_diag_iter di = start; di != end; ++di) {
		int jbar = (*di).getIndex();
		if ((*di).isReal()) {
			KronVector xi(x, jbar);
			xi.zeros();
			Vector wi(work, (jbar-si)*xi.length(), xi.length());
			xi.add(*((*di).getAlpha()), wi);
			for (const_row_iter ri = row_begin(*di); ri != row_end(*di); ++ri) {
				int col = ri.getCol();
				Vector wj(work, (col-si)*xi.length(), xi.length());
				xi.add(*ri, wj);
			}
		} else {
			KronVector xi(x, jbar);
			KronVector xii(x, jbar+1);
			xi.zeros();
			xii.zeros();
			Vector wi(work, (jbar-si)*xi.length(), xi.length());
			Vector wii(work, (jbar+1-si)*xi.length(), xi.length());
			xi.add(*((*di).getAlpha()), wi);
			xi.add((*di).getBeta1(), wii);
			xii.add((*di).getBeta2(), wi);
			xii.add(*((*di).getAlpha()), wii);
			for (const_row_iter ri = row_begin(*di); ri != row_end(*di); ++ri) {
				int col = ri.getCol();
				Vector wj(work, (col-si)*xi.length(), xi.length());
				xi.add(ri.a(), wj);
				xii.add(ri.b(), wj);
			}
		}
	}
}
