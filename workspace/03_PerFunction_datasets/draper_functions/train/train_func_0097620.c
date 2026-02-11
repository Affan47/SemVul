methods( const KJS::UString &className )
{
    return KJSEmbed::g_ctorHash[toQString(className)]->methods;
}
