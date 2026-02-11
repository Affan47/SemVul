FFTBandPassFilterFormat( double lo, double hi, wxPlotData::FFTFilter_Type filter, double n )
{
    switch (filter)
    {
        case FilterStep        : return wxString::Format(wxT("(x>%lg)&(x<%lg)"), lo, hi);
        case FilterButterworth : return wxString::Format(wxT("1 - (1/(1+(x/%lg)^(2*%lg))+(1-1/(1+(x/%lg)^(2*%lg))))"), lo, n, hi, n);
        case FilterGaussian    : return wxString::Format(wxT("exp(-(%lg^2)/(2*x*x)) - exp(-(%lg^2)/(2*x*x))"), lo, hi);
        case FilterFermi       : return wxString::Format(wxT("1 - 1/(1+exp((%lg-x)/(-%lg))) - 1/(1+exp((%lg-x)/(%lg)))"), lo, n, hi, n);
        default : break;
    }
    return wxEmptyString;
}
