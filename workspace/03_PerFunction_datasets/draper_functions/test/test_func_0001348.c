string_unbox(object_t self) {
    if (!object_is_string(self))
        fail();
    return (char *)self.data.pointer;
}
