clBuildProgram(
cl_program program,
cl_uint num_devices,
const cl_device_id *device_list,
const char *options,
void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data),
void *user_data)
{
    char cmd[256];
    DEBUG("clBuildProgram called\n");
    if(program == NULL){
        DEBUG("Warning: Program is NULL");
        return CL_INVALID_PROGRAM;
    }
    program->buildStatus = CL_BUILD_IN_PROGRESS;

    if(program->createdWithBinary == CL_TRUE){
        program->buildStatus = CL_BUILD_SUCCESS;
        return CL_SUCCESS;
    }
    if(program->buildOptions){
        free(program->buildOptions);
    }
    program->buildOptions = strdup(options);
    program->buildOptionsLen = strlen(options);
    DEBUG("clBuildProgram: buildoptions %s\n", options);

    DEBUG("clBuildProgram: safe buildoptions %s\n", options);
    FILE *optionsFile = fopen("tmp.options", "wb+");
    if (optionsFile != NULL){
        fwrite("CLFLAGS=\"", 9, 1, optionsFile);
        fwrite(options, strlen(options), 1, optionsFile);
        fwrite("\"", 1, 1, optionsFile);
        fclose(optionsFile);
        optionsFile = NULL;
    }else{
        DEBUG("%s: build options store failed.\n", __func__);
        program->buildStatus = CL_BUILD_ERROR;
        return CL_BUILD_PROGRAM_FAILURE;
    }

    FILE *srcFile = fopen("tmp.cl", "wb+");

    if (srcFile != NULL){
        int line;
        for(line = 0; line < program->source.count; line++){
            DEBUG("%s: Line length %d\n", __func__, program->source.lengths[line]);
            fwrite(program->source.strings[line], program->source.lengths[line] - 1, 1, srcFile);
        }
        fclose(srcFile);

        DEBUG("%s: performing program build\n", __func__);
        snprintf(cmd, 256, "$NOVELCLSDKROOT/scripts/buildprogram.sh tmp.cl ");
        DEBUG("RUN: %s", cmd);
        if(system(cmd)){
            DEBUG("%s: program build error\n", __func__);
            program->buildStatus = CL_BUILD_ERROR;
            return CL_BUILD_PROGRAM_FAILURE;
        }
        DEBUG("%s: program build success\n", __func__);
        FILE * binaryFile = fopen("program.o", "rb");
        if(binaryFile != NULL){
            fseek(binaryFile, 0L, SEEK_END);
            program->binarySize = ftell(binaryFile);
            fclose(binaryFile);
        }else{
            program->buildStatus = CL_BUILD_ERROR;
            return CL_BUILD_PROGRAM_FAILURE;
        }
        program->hasBinary = CL_TRUE;
        program->buildStatus = CL_BUILD_SUCCESS;
        return CL_SUCCESS;

    }else{
        DEBUG("%s: Failed\n", __func__);
        program->buildStatus = CL_BUILD_ERROR;
        return CL_BUILD_PROGRAM_FAILURE;
    }
}
