requestRenderBuffer(GLenum format, uint32 width, uint32 height, uint fsaa)
    {
        GLSurfaceDesc retval;
        retval.buffer = 0;
        if(format != GL_NONE)
        {
            RBFormat key(format, width, height, fsaa);
            RenderBufferMap::iterator it = mRenderBufferMap.find(key);
            if(it != mRenderBufferMap.end() && (it->second.refcount == 0))
            {
                retval.buffer = it->second.buffer;
                retval.zoffset = 0;
                retval.numSamples = fsaa;

                ++it->second.refcount;
            }
            else
            {

                GLRenderBuffer *rb = new GLRenderBuffer(format, width, height, fsaa);
                mRenderBufferMap[key] = RBRef(rb);
                retval.buffer = rb;
                retval.zoffset = 0;
                retval.numSamples = fsaa;
            }
        }

        return retval;
    }
