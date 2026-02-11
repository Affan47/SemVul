loadData()
{
    m_loading = true;

    switch ( m_type.fractal() ) {
        case MandelbrotFractal:
            m_ui.radioMandelbrot->setChecked( true );
            break;
        case JuliaFractal:
            m_ui.radioJulia->setChecked( true );
            m_ui.editJuliaX->setValue( m_type.parameter().x() );
            m_ui.editJuliaY->setValue( m_type.parameter().y() );
            break;
    }

    switch ( m_type.variant() ) {
        case GeneratorCore::NormalVariant:
            m_ui.radioNormal->setChecked( true );
            break;
        case GeneratorCore::ConjugateVariant:
            m_ui.radioConjugate->setChecked( true );
            break;
        case GeneratorCore::AbsoluteVariant:
            m_ui.radioAbsolute->setChecked( true );
            break;
        case GeneratorCore::AbsoluteImVariant:
            m_ui.radioAbsoluteIm->setChecked( true );
            break;
    }

    switch ( m_type.exponentType() ) {
        case IntegralExponent:
            m_ui.radioIntegral->setChecked( true );
            m_ui.spinIntegral->setValue( m_type.integralExponent() );
            break;
        case RealExponent:
            m_ui.radioReal->setChecked( true );
            m_ui.spinReal->setValue( m_type.realExponent() );
            break;
    }

    m_loading = false;
}
