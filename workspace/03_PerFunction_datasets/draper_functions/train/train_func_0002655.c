SetStyleTable (
    OGRStyleTable * poStyleTable )
{

    if ( !bUpdate )
        return;

    if ( poStyleTable )
        SetStyleTableDirectly ( poStyleTable->Clone (  ) );
    else
        SetStyleTableDirectly ( NULL );
    return;
}
