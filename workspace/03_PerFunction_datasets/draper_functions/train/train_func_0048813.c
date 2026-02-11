StackMe(int mySize)
    {
        mySize += 3;
        int pos = 0;

        if(!widths.empty())
            pos = *(std::max_element(widths.begin(), widths.end()));

        widths.push_back(pos + mySize);
        return pos + mySize;
    }
