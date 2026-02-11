textObj_draw_bound( textObj * obj, int hbound, int vbound )
{
    VMfloat x=0.0;
    VMfloat y=0.0;
    if(! obj->is_3D){
        if( hbound == HBOUND_CENTER )  x=-(VMfloat)(obj->quad_w)/2.0;
        if( hbound == HBOUND_RIGHT  )  x=-(VMfloat)(obj->quad_w);
        if( hbound == HBOUND_LEFT   )  x=0.0;
        if( vbound == VBOUND_CENTER )  y=-(VMfloat)(obj->quad_h)/2.0;
        if( vbound == VBOUND_TOP    )  y=-(VMfloat)(obj->quad_h);
        if( vbound == VBOUND_BOTTOM )  y=0.0;
        glPushMatrix();
        glTranslatef( x, y, 0.0 );
        if( obj->quad_id != 0 )
            glCallList( obj->quad_id );
        glPopMatrix();
    } else {
        if( hbound == HBOUND_CENTER )  x=-(VMfloat)(obj->obj3D_w)/2.0;
        if( hbound == HBOUND_RIGHT  )  x=-(VMfloat)(obj->obj3D_w);
        if( hbound == HBOUND_LEFT   )  x=0.0;
        if( vbound == VBOUND_CENTER )  y=-(VMfloat)(obj->obj3D_h)/2.0;
        if( vbound == VBOUND_TOP    )  y=-(VMfloat)(obj->obj3D_h);
        if( vbound == VBOUND_BOTTOM )  y=0.0;
        glPushMatrix();
        glTranslatef( x, y, 0.0 );
        if( obj->obj3D_id != 0 ){
            glCallList( obj->obj3D_id );
        }
        glPopMatrix();
    }
}
