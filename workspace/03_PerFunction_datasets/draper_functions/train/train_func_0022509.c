gamgi_math_hash_value (const char *name,
unsigned int multiplier, unsigned int size)
{
unsigned int hash;
unsigned char *pointer;

hash = 0;

for (pointer = (unsigned char *) name; *pointer != '\0'; pointer++)
  hash = multiplier * hash + *pointer;

return hash % size;
}
