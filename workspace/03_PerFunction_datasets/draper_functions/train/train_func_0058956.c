SetCoefficients(
    const std::vector<double>& xnum, const std::vector<double>& xdenom,
    const std::vector<double>& ynum, const std::vector<double>& ydenom)
{
    if (xnum.size() != xdenom.size() || ynum.size() != ydenom.size() ||
        xnum.size() != ynum.size() || xdenom.size() != ydenom.size()) {
        throw PCIDSKException("All RPC coefficient vectors must be the "
            "same size.");
    }

    pimpl_->pixel_num = xnum;
    pimpl_->pixel_denom = xdenom;
    pimpl_->line_num = ynum;
    pimpl_->line_denom = ydenom;
    mbModified = true;
}
