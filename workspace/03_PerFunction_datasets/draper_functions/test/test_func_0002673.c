operator<(const ToolbarFitInfo &r) const
    {
        if (row < r.row)
            return true;
        else if (row == r.row)
            return rect.x < r.rect.x;
        else
            return false;
    }
}
