printFooterLine(ofstream *psOutFile, int fr,int lr)
{
    int i;
    int psX, psY;

    psX = LEFTMARGIN;
    psY = footerTop;
    (*psOutFile) << psX << " " << psY << " moveto\n";
    (*psOutFile) << "(" << setw(data->alignPtr->getMaxNames()) << " ) show\n";

    for(i = fr; i <= lr && i < ruler.length(); i++)
    {
        psX = blockLeft + (i - fr) * CHARWIDTH;
        (*psOutFile) <<  "(";
        (*psOutFile) << ruler[i];
        (*psOutFile) << ") ";
        (*psOutFile) << psX << " " << psY << " " << psX << " " << psY
                     << " 1.0 1.0 1.0 color_inv\n";
    }

    (*psOutFile) << "\n";
}
