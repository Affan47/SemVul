textObj_delete( textObj * obj )
{
    if(! obj->is_3D){
        glDeleteLists( obj->quad_id, 1 );
        obj->quad_id=0;
        glDeleteTextures( 1, (GLuint *)&(obj->tex_id) );
        obj->tex_id=0;
    } else {
        glDeleteLists( obj->obj3D_id, 1 );
        obj->obj3D_id=0;
    }
}
