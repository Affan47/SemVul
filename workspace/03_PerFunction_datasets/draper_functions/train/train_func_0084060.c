propertySetterDefinition( const Property* property, const ResourceClass* rc ) const
{
    QString s = propertySetterDeclaration( property, rc, "NepomukFast" ) + '\n';

    s += QLatin1String("{\n");
    if ( !property->isList() ) {
        if ( property->hasSimpleType() ) {
            s += QString::fromLatin1("    addProperty( QUrl::fromEncoded(\"%1\"), Soprano::LiteralValue( value ) );\n").arg( property->uri().toString() );
        } else {
            s += QString::fromLatin1("    addProperty( QUrl::fromEncoded(\"%1\"), value.uri() );\n").arg( property->uri().toString() );
        }
    } else {
        if ( property->hasSimpleType() ) {
            s += QString::fromLatin1("    for( %1::const_iterator it = value.constBegin();\n"
                                     "         it != value.constEnd(); ++it ) {\n"
                                     "       addProperty( QUrl::fromEncoded(\"%2\"), Soprano::LiteralValue( *it ) );\n"
                                     "    }\n").arg( property->typeString() ).arg( property->uri().toString() );
        } else {
            s += QString::fromLatin1("    for( %1::const_iterator it = value.constBegin();\n"
                                     "         it != value.constEnd(); ++it ) {\n"
                                     "       addProperty( QUrl::fromEncoded(\"%2\"), (*it).uri() );\n"
                                     "    }\n").arg( property->typeString() ).arg( property->uri().toString() );
        }
    }
    s += QLatin1String("}\n");

    return s;
}
