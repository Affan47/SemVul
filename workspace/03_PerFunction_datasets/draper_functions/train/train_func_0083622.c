propertyAdderDefinition( const Property* property, const ResourceClass* rc ) const
{
    QString s = propertyAdderDeclaration( property, rc, "NepomukFast" ) + '\n';

    s += QLatin1String("{\n");
    if ( property->hasSimpleType() ) {
        s += QString::fromLatin1("    addProperty( QUrl::fromEncoded(\"%1\"), Soprano::LiteralValue( value ) );\n").arg( property->uri().toString() );
    } else {
        s += QString::fromLatin1("    addProperty( QUrl::fromEncoded(\"%1\"), value.uri() );\n").arg( property->uri().toString() );
    }
    s += QLatin1String("}\n");

    return s;
}
