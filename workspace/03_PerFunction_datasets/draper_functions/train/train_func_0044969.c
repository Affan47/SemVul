get_dltmat(DMATRIX mat, DWin *dw, int dno, DMATRIX dmat)
{
    int i, j, k, tmpnum;

    tmpnum = (int)mat->row - dw->width[dno][WRIGHT];
    for (k = dw->width[dno][WRIGHT]; k < tmpnum; k++)
	for (i = 0; i < (int)mat->col; i++)
	    for (j = dw->width[dno][WLEFT], dmat->data[k][i] = 0.0;
		 j <= dw->width[dno][WRIGHT]; j++)
		dmat->data[k][i] += mat->data[k + j][i] * dw->coef[dno][j];

    for (i = 0; i < (int)mat->col; i++) {
	for (k = 0; k < dw->width[dno][WRIGHT]; k++)
	    for (j = dw->width[dno][WLEFT], dmat->data[k][i] = 0.0;
		 j <= dw->width[dno][WRIGHT]; j++)
		if (k + j >= 0)
		    dmat->data[k][i] += mat->data[k + j][i] * dw->coef[dno][j];
		else
		    dmat->data[k][i] += (2.0 * mat->data[0][i] - mat->data[-k - j][i]) * dw->coef[dno][j];
	for (k = tmpnum; k < (int)mat->row; k++)
	    for (j = dw->width[dno][WLEFT], dmat->data[k][i] = 0.0;
		 j <= dw->width[dno][WRIGHT]; j++)
		if (k + j < (int)mat->row)
		    dmat->data[k][i] += mat->data[k + j][i] * dw->coef[dno][j];
		else
		    dmat->data[k][i] += (2.0 * mat->data[mat->row - 1][i] - mat->data[mat->row - k - j + mat->row - 2][i]) * dw->coef[dno][j];
    }

    return;
}
