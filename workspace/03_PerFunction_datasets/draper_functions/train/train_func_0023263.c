DrawSnake(wxDC* DC)
{
    for ( int i=0; i<m_SnakeLen; i++ )
    {
        DrawBrick(DC,m_SnakeX[i]+1,m_SnakeY[i]+3,GetColour(m_SnakeColour));
    }
}
