maxWidthPerClient() const {
    switch (alignment()) {
    case RIGHT:
    case CENTER:
    case LEFT:
        return m_max_size_per_client;
        break;
    case RELATIVE:
        if (size() == 0)
            return width();
        else {
            unsigned int borderW = m_item_list.front()->borderWidth();


            unsigned int w = width(), h = height();
            translateSize(m_orientation, w, h);
            if (w < (size()-1)*borderW)
                return 1;
            else
                return (w - (size() - 1) * borderW) / size();
        }
        break;
    }


    return 1;
}
