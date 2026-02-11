DeselectBlock( const wxBlockDouble &block, bool combineNow)
{


    bool done = false;

    wxBlockDouble top, bottom, left, right;
    for (int n=0; n<int(m_blocks.GetCount()); n++)
    {
        if (m_blocks[n].Delete(block, top, bottom, left, right))
        {
            done = true;
            m_blocks.RemoveAt(n);
            n = (n > 0) ? n - 1 : -1;

            if (!top.IsEmpty())    m_blocks.Add(top);
            if (!bottom.IsEmpty()) m_blocks.Add(bottom);
            if (!left.IsEmpty())   m_blocks.Add(left);
            if (!right.IsEmpty())  m_blocks.Add(right);
        }
    }

    if (combineNow)
        Minimize();

    return done;
}
