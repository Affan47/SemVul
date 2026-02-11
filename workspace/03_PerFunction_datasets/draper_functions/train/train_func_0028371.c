ShallowEqual( const XMLNode* compare ) const
{
    return ( compare->ToDeclaration() && XMLUtil::StringEqual( compare->ToDeclaration()->Value(), Value() ));
}
