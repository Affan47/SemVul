saveParameters()
{
    if ( !m_loading ) {
        FractalType type = m_model->fractalType();
        if ( type.fractal() == JuliaFractal ) {
            type.setParameter( QPointF( m_ui.editJuliaX->value(), m_ui.editJuliaY->value() ) );
            m_model->setFractalType( type );
        }
    }
}
