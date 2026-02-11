shiftUp() {
    for (int z=0; z<m_depth; z++) {

	for (int x=0; x<m_width; x++) {
	    if (getBoardData(z,0,x) == '1') {
		setBoardData(z,0,x,0);
		if (x<m_width-1) {
			setBoardData(z,0,x+1,0);
			setBoardData(z,1,x+1,0);
		}
		setBoardData(z,1,x,0);
	    }
	}
    }
    for (int z=0; z<m_depth;z++) {
	for (int y=0; y<m_height-1; y++) {
	    for (int x=0; x<m_width; x++) {
		setBoardData(z,y,x,getBoardData(z,y+1,x));
		if (y == m_height-2)
			setBoardData(z,y+1,x,0);
	    }
        }
    }
}
