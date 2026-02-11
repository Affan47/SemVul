mergeAdjacentTexcoords( unsigned short finalTexCoordSet,
                                        unsigned short texCoordSetToDestroy,
                                        VertexData *vertexData )
    {
        VertexDeclaration *vDecl    = vertexData->vertexDeclaration;

        const VertexElement *uv0 = vDecl->findElementBySemantic( VES_TEXTURE_COORDINATES,
                                                                    finalTexCoordSet );
        const VertexElement *uv1 = vDecl->findElementBySemantic( VES_TEXTURE_COORDINATES,
                                                                    texCoordSetToDestroy );

        if( uv0 && uv1 )
        {

            VertexElementType baseType0 = VertexElement::getBaseType( uv0->getType() );
            VertexElementType baseType1 = VertexElement::getBaseType( uv1->getType() );

            unsigned short totalTypeCount = VertexElement::getTypeCount( uv0->getType() ) +
                                            VertexElement::getTypeCount( uv1->getType() );
            if( baseType0 == baseType1 && totalTypeCount <= 4 )
            {
                const VertexDeclaration::VertexElementList &veList = vDecl->getElements();
                VertexDeclaration::VertexElementList::const_iterator uv0Itor = std::find( veList.begin(),
                                                                                    veList.end(), *uv0 );
                unsigned short elem_idx     = std::distance( veList.begin(), uv0Itor );
                VertexElementType newType   = VertexElement::multiplyTypeCount( baseType0,
                                                                                totalTypeCount );

                if( ( uv0->getOffset() + uv0->getSize() == uv1->getOffset() ||
                      uv1->getOffset() + uv1->getSize() == uv0->getOffset() ) &&
                    uv0->getSource() == uv1->getSource() )
                {

                    size_t newOffset        = std::min( uv0->getOffset(), uv1->getOffset() );
                    unsigned short newIdx   = std::min( uv0->getIndex(), uv1->getIndex() );

                    vDecl->modifyElement( elem_idx, uv0->getSource(), newOffset, newType,
                                            VES_TEXTURE_COORDINATES, newIdx );
                    vDecl->removeElement( VES_TEXTURE_COORDINATES, texCoordSetToDestroy );
                    uv1 = 0;
                }

                vDecl->closeGapsInSource();
            }
        }
    }
