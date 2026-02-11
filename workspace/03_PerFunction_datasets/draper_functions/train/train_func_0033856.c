checkSelectionPoint( int _x, int _y, int _tx, int _ty, DOM::NodeImpl*& node, int & offset, SelPointState &state )
{
    int off = offset;
    DOM::NodeImpl* nod = node;

    FindSelectionResult pos;
    TableSectionIterator it(this);
    for (; *it; ++it) {
        pos = (*it)->checkSelectionPoint(_x, _y, _tx + m_x, _ty + m_y, nod, off, state);
        switch(pos) {
        case SelectionPointBeforeInLine:
        case SelectionPointInside:

            node = nod;
            offset = off;
            return SelectionPointInside;
        case SelectionPointBefore:

            if ( state.m_lastNode ) {
                node = state.m_lastNode;
                offset = state.m_lastOffset;


                return SelectionPointInside;
            } else {
                node = nod;
                offset = off;

                return SelectionPointBefore;
            }
            break;
        case SelectionPointAfter:
	    if (state.m_afterInLine) break;

        case SelectionPointAfterInLine:
	    if (pos == SelectionPointAfterInLine) state.m_afterInLine = true;

            state.m_lastNode = nod;
            state.m_lastOffset = off;

            break;
        }
    }


    if ( state.m_lastNode )
    {
        node = state.m_lastNode;
        offset = state.m_lastOffset;
    }

    return SelectionPointAfter;
}
