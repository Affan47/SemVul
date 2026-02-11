parsenumber(struct compiling *c, const char *s)
{
        const char *end;
        long x;
        double dx;
#ifndef WITHOUT_COMPLEX
        Py_complex complex;
        int imflag;
#endif

        assert(s != NULL);
        errno = 0;
        end = s + strlen(s) - 1;
#ifndef WITHOUT_COMPLEX
        imflag = *end == 'j' || *end == 'J';
#endif
        if (*end == 'l' || *end == 'L')
                return PyLong_FromString((char *)s, (char **)0, 0);
        x = PyOS_strtol((char *)s, (char **)&end, 0);
        if (*end == '\0') {
                if (errno != 0)
                        return PyLong_FromString((char *)s, (char **)0, 0);
                return PyInt_FromLong(x);
        }

#ifndef WITHOUT_COMPLEX
        if (imflag) {
                complex.real = 0.;
                complex.imag = PyOS_string_to_double(s, (char **)&end, NULL);
                if (complex.imag == -1.0 && PyErr_Occurred())
                        return NULL;
                return PyComplex_FromCComplex(complex);
        }
        else
#endif
        {
                dx = PyOS_string_to_double(s, NULL, NULL);
                if (dx == -1.0 && PyErr_Occurred())
                        return NULL;
                return PyFloat_FromDouble(dx);
        }
}
