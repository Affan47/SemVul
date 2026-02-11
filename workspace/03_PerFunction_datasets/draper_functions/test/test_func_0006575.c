string_append_range( string * self, char const * start, char const * finish )
{
    size_t rhs_size = finish - start;
    size_t new_size = self->size + rhs_size;
    assert_invariants( self );

    maybe_reserve( self, new_size );

    memcpy( self->value + self->size, start, rhs_size );
    self->size = new_size;
    self->value[ new_size ] = 0;

    assert_invariants( self );
}
