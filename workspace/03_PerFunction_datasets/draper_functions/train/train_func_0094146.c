clearTriangles()
{
    QList<BookmarkTriangle *>::iterator i;
    for( i = m_triangles.begin(); i != m_triangles.end(); ++i ){
      (*i)->deleteLater();
    }
    m_triangles.clear();
}
