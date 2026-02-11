resourcePseudoInheritanceDeclaration( const ResourceClass* baseRc, const ResourceClass* rc, const QString &nameSpace ) const
{
    return QString( "%1 %2to%3() const" )
        .arg( rc->name( nameSpace ) )
        .arg( !nameSpace.isEmpty() ? baseRc->name( "Nepomuk" ) + "::" : QString() )
        .arg( rc->name() );
}
