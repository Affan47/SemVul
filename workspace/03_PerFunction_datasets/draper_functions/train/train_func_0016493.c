getDrawColour(wxColour &graphColour, int number) {
	switch (number % 10){
	case 1:	graphColour = m_pen_GraphColour01;	break;
	case 2:	graphColour = m_pen_GraphColour02;	break;
	case 3:	graphColour = m_pen_GraphColour03;	break;
	case 4:	graphColour = m_pen_GraphColour04;	break;
	case 5: graphColour = m_pen_GraphColour05;	break;
	case 6:	graphColour = m_pen_GraphColour06;	break;
	case 7:	graphColour = m_pen_GraphColour07;	break;
	case 8:	graphColour = m_pen_GraphColour08;	break;
	case 9: graphColour = m_pen_GraphColour09;	break;
	default:graphColour = m_pen_GraphColour00;
	}
}
