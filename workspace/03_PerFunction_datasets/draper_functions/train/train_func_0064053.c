shiftRight() {
    for (int z=0; z<m_depth; z++) {
	for (int y=0; y<m_height; y++) {
	    UCHAR keep=getBoardData(z,y,m_width-2);
	    if (keep == '1') {

	        setBoardData(z,y,m_width-2,0);
	        setBoardData(z,y,m_width-1,0);
		if (y < m_height-1) {
		        setBoardData(z,y+1,m_width-2,0);
		        setBoardData(z,y+1,m_width-1,0);
		}
	    }
	    for (int x=m_width-1; x>0; x--) {
		setBoardData(z,y,x,getBoardData(z,y,x-1));
	    }
	    setBoardData(z,y,0,0);
	}
    }
}
