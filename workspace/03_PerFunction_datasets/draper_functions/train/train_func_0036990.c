OnLineThickness( int val )
{
  dynamic_cast<GraphicsPage*>(ExGlobals::GetVisualizationWindow()->GetPage())->SetFigureLineThickness( val );
}
