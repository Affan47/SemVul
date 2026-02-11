setpixel ( INT32 x,INT32 y,COLORT color )
{
	if ( (x<0) || (x>=m_width) || (y<0) || (y>=m_height) )
	    return;
	*(UINT32 *)( m_ptrscr + y * m_width + x ) = color;
}
