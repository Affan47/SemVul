createFunctor( const FractalType& type )
{
    switch ( type.exponentType() ) {
        case IntegralExponent:
            if ( type.fractal() == MandelbrotFractal ) {
                return GeneratorCore::createMandelbrotFastFunctor( type.integralExponent(), type.variant() );
            } else {
                return GeneratorCore::createJuliaFastFunctor( type.parameter().x(),
                    type.parameter().y(), type.integralExponent(), type.variant() );
            }
            break;

        case RealExponent:
            if ( type.fractal() == MandelbrotFractal ) {
                return GeneratorCore::createMandelbrotFunctor( type.realExponent(), type.variant() );
            } else if ( type.fractal() == JuliaFractal ) {
                return GeneratorCore::createJuliaFunctor( type.parameter().x(),
                    type.parameter().y(), type.realExponent(), type.variant() );
            }
            break;
    }

    return NULL;
}
